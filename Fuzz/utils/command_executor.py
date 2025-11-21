import os
import pathlib
import threading
import time

if os.name == "nt":
    from .windows.batch_executor import BatchExecutor as ScriptExecutor
elif os.name == "posix":
    from .ubuntu.bash_executor import BashExecutor as ScriptExecutor
else:
    raise Exception("unsupported operation system!")

from .logger import SUCCESS, STATUS, ERROR, INFO


class CommandExecutor:
    """
    This class is used to execute commands and log their output in both sources:
    1) to the standard output;
    2) to the corresponded log file.
    Additionally, this class checks the return code of executed operation and measures the time duration of its execution.
    """

    def __init__(self, ctx):
        self._log_dir = ctx.current_instance_log
        self._execute_created_script = ctx.config.run_time.execute_created_script
        pathlib.Path(ctx.current_instance_log).mkdir(parents=True, exist_ok=True)
        self._executor = ScriptExecutor()

    def execute(self, command: list, *, cwd: str = None, env: dict = None, log: str = None):
        log_path = pathlib.Path(f"{self._log_dir}/{log}")
        [process_handler, script_path] = self._executor.get_execute_process_handler(validate_commands(command), cwd=cwd, env=env, log_path=log_path)

        if self._execute_created_script == False:
            STATUS \
                .log_line("\nWithout execution:") \
                .log_line(f"Command script file: {script_path}")
            return

        start_time = time.time()

        # open log-file for rewriting
        log_file = open(log_path, "w", encoding="utf-8")

        def write_log_line(line):
            # write in console
            INFO.log_line(f"{line.rstrip()}")
            # write in log-file
            log_file.write(f"{line}")
            log_file.flush()

        def read_stream(stream, stream_type):
            for line in stream:
                write_log_line(f"[{stream_type}] {line}")

        stdout_thread = threading.Thread(target=read_stream, args=(process_handler.stdout, "stdout"))
        stderr_thread = threading.Thread(target=read_stream, args=(process_handler.stderr, "stderr"))

        stdout_thread.start()
        stderr_thread.start()

        stdout_thread.join()
        stderr_thread.join()

        return_code = process_handler.wait()
        end_time = time.time()
        duration = end_time - start_time

        # write summary about execution-time and return-code
        summary = f"\n=== Duration: {duration:.3f} seconds ===\n=== Return code: {return_code} ===\n"
        write_log_line(summary)

        log_file.close()

        STATUS \
            .log_line(f"\nCommand script file: {script_path}") \
            .log_line(f"Command log file: {log_path}") \

        if return_code == 0:
            SUCCESS.log_line("Command completed successfully.")
        else:
            ERROR.log_line(f"Command failed: return code {return_code}.")
            raise Exception("command execution error!")


def is_list_of_lists(obj):
    return isinstance(obj, list) and all(isinstance(x, list) for x in obj)


def validate_commands(commands):
    clean_command = [cmd for cmd in commands if cmd is not None]
    # If command is a flat list, wrap it in another list
    single_command = isinstance(clean_command, list) and (not is_list_of_lists(clean_command))
    clean_commands = []
    for cmd in [clean_command] if single_command else clean_command:
        # remove all None elements from command
        clean_cmd = [x for x in cmd if x is not None]
        clean_commands.append(clean_cmd)
    return clean_commands
