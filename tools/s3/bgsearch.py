"""bgsearch.py: unattended low-priority searches (Windows).

  bgsearch.py start NAME SCRIPT ARGS...   run tools/s3/SCRIPT ARGS... --work build/s3_perm/NAME/work through
                                          tools/lowprio.py (idle priority, one job), detached; output to
                                          build/s3_perm/NAME/log.txt
  bgsearch.py list                        each search: running or its exit code, match file, last log line
  bgsearch.py stop NAME                   end a running search (and its compiles)

SCRIPT is one of the searches that take --work (permtry.py, topotry.py, voltry.py, ordtry.py, floattry.py,
irsbatch.py). At most two run at a time.
Everything stays under build/s3_perm (ignored by git); the PID is in NAME/pid and in build/s3_perm/pids.txt. A
search's own exit code goes to NAME/exit.txt: 0 means it wrote its match file (perm_match.cpp, topo_match.cpp or
vol_match.cpp; irsbatch.py: irs_match_ADDR.ll, an IR order still to be written as source) into NAME/work. A hit still has to be put into its unit and pass the full check before it counts.
"""
import os, re, sys, subprocess, time, ctypes
M = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))  # the matching/ folder
S3 = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.join(M, "build", "s3_perm")
IDLE, DETACHED, NEWGROUP = 0x40, 0x08, 0x200
MAXRUN = 2


def alive(pid):
    h = ctypes.windll.kernel32.OpenProcess(0x1000, False, pid)  # PROCESS_QUERY_LIMITED_INFORMATION
    if not h:
        return False
    code = ctypes.c_ulong()
    ok = ctypes.windll.kernel32.GetExitCodeProcess(h, ctypes.byref(code))
    ctypes.windll.kernel32.CloseHandle(h)
    return bool(ok) and code.value == 259  # STILL_ACTIVE


def searches():
    if not os.path.isdir(ROOT):
        return []
    out = []
    for n in sorted(os.listdir(ROOT)):
        d = os.path.join(ROOT, n)
        if os.path.isfile(os.path.join(d, "pid")):
            pid = int(open(os.path.join(d, "pid")).read().split()[0])
            out.append((n, d, pid))
    return out


def main():
    if len(sys.argv) < 2:
        print(__doc__); return 2
    cmd = sys.argv[1]
    if cmd == "_run":  # the detached wrapper: run the search, record its exit code
        name, script, rest = sys.argv[2], sys.argv[3], sys.argv[4:]
        d = os.path.join(ROOT, name)
        with open(os.path.join(d, "log.txt"), "a", encoding="utf-8") as log:
            r = subprocess.run([sys.executable, "-B", "-I", os.path.join(S3, script), *rest, "--work", os.path.join(d, "work")],
                               stdout=log, stderr=subprocess.STDOUT, cwd=M)
        open(os.path.join(d, "exit.txt"), "w").write(f"{r.returncode} {time.strftime('%Y-%m-%d %H:%M:%S')}\n")
        return 0
    if cmd == "start":
        name, script, rest = sys.argv[2], sys.argv[3], sys.argv[4:]
        if not os.path.isfile(os.path.join(S3, script)):
            print("no such script:", script); return 2
        running = [n for n, d, pid in searches() if alive(pid) and not os.path.exists(os.path.join(d, "exit.txt"))]
        if len(running) >= MAXRUN:
            print("already running:", ", ".join(running)); return 1
        d = os.path.join(ROOT, name)
        if os.path.exists(d):
            print("exists:", d, "(pick another name)"); return 1
        os.makedirs(os.path.join(d, "work"))
        with open(os.path.join(d, "log.txt"), "w", encoding="utf-8") as log:
            log.write(f"# {time.strftime('%Y-%m-%d %H:%M:%S')} {script} {' '.join(rest)}\n")
        # through tools/lowprio.py (idle priority, one job), detached so it outlives this call
        p = subprocess.Popen([sys.executable, "-B", "-I", os.path.join(M, "tools", "lowprio.py"), "--jobs", "1", "--",
                              sys.executable, "-B", "-I", os.path.abspath(__file__), "_run", name, script, *rest], cwd=M,
                             creationflags=IDLE | DETACHED | NEWGROUP, stdin=subprocess.DEVNULL,
                             stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, close_fds=True)
        open(os.path.join(d, "pid"), "w").write(f"{p.pid}\n")
        with open(os.path.join(ROOT, "pids.txt"), "a") as f:
            f.write(f"{p.pid}\t{name}\t{time.strftime('%Y-%m-%d %H:%M:%S')}\t{script} {' '.join(rest)}\n")
        print("started", name, "pid", p.pid); return 0
    if cmd == "list":
        for n, d, pid in searches():
            ex = os.path.join(d, "exit.txt")
            state = ("exit " + open(ex).read().split()[0]) if os.path.exists(ex) else ("running" if alive(pid) else "gone")
            w = os.path.join(d, "work")
            hits = sorted(f for f in (os.listdir(w) if os.path.isdir(w) else []) if re.fullmatch(r"\w+_match(_\w+)?\.(cpp|ll)", f))
            lines = open(os.path.join(d, "log.txt"), encoding="utf-8", errors="replace").read().strip().split("\n")
            print(f"{n}\tpid {pid}\t{state}\t{','.join(hits) or '-'}\t{lines[-1][:120]}")
        return 0
    if cmd == "stop":
        for n, d, pid in searches():
            if n == sys.argv[2] and alive(pid):
                subprocess.run(["taskkill", "/PID", str(pid), "/T", "/F"], capture_output=True)
                print("stopped", n)
        return 0
    print(__doc__); return 2


if __name__ == "__main__":
    sys.exit(main())
