"""Run a command at low CPU priority so unattended searches never slow the compile jobs of the other sessions.

usage: lowprio.py [--jobs N] [--below] -- COMMAND [ARGS...]

The command starts at IDLE_PRIORITY_CLASS (BELOW_NORMAL_PRIORITY_CLASS with --below); every process it starts,
compilers included, inherits that class. --jobs caps the parallelism of the tools that read RV_JOBS or JOBS
(default 1, the job share of a hand-matching session). The exit code is the command's.
"""
import os
import subprocess
import sys

IDLE_PRIORITY_CLASS = 0x00000040
BELOW_NORMAL_PRIORITY_CLASS = 0x00004000


def main():
    args = sys.argv[1:]
    jobs, flag = 1, IDLE_PRIORITY_CLASS
    while args and args[0] != "--":
        a = args.pop(0)
        if a == "--jobs":
            jobs = max(1, int(args.pop(0)))
        elif a == "--below":
            flag = BELOW_NORMAL_PRIORITY_CLASS
        else:
            sys.exit(__doc__)
    if not args or args[0] != "--" or len(args) < 2:
        sys.exit(__doc__)
    cmd = args[1:]
    env = dict(os.environ, RV_JOBS=str(jobs), JOBS=str(jobs))
    kwargs = {"creationflags": flag} if os.name == "nt" else {"preexec_fn": lambda: os.nice(19)}
    sys.exit(subprocess.call(cmd, env=env, **kwargs))


if __name__ == "__main__":
    main()
