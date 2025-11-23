import os
from pathlib import Path
from invoke import task, Collection

import setup
from utils.logger import INFO
from utils.command_executor import CommandExecutor


@task(pre=[setup.setup_context])
def get_info(ctx):
    """
    Print to console information about active configuration of invoke-tasks
    """
    env_context = setup.get_env_context()

    # Define custom formatters for string columns
    formatters = {}
    for col in env_context.select_dtypes(include='object').columns:
        max_len = env_context[col].astype(str).str.len().max()
        formatters[col] = lambda x, length=max_len: f"  {x:<{length}s}"

    INFO.log_line("Active environment configuration:") \
        .log_line(f"{env_context.to_string(formatters=formatters, index=False)}")


@task(pre=[setup.setup_context])
def yapf(ctx):
    """
    Format python files in Fuzz
    """

    def collect_file(dir):
        files = []
        for item in os.listdir(dir):
            item = Path(os.path.join(f'{dir}', item))
            if item.is_file():
                if item.name.endswith('.py'):
                    files.append(f'"{item.as_posix()}"')
            elif item.is_dir():
                if not item.name.startswith('.'):
                    files.extend(collect_file(f'{item.as_posix()}'))
        return files

    CommandExecutor(ctx)\
        .add_cwd(f"{ctx.fuzz_dir}")\
        .add_command([
                "yapf",
                "--style .style.yapf",
                "--verbose",
                "--in-place",
                *collect_file(f"{ctx.fuzz_dir}")
            ])\
        .execute(log="yapf.log")


namespace = Collection()
namespace.add_task(get_info, name="get-info")
namespace.add_task(yapf, name="yapf")

import leet_code

namespace.add_collection(leet_code.collection)
