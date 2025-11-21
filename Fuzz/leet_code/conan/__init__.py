from invoke import Collection, task

import setup
from utils.command_executor import CommandExecutor
from utils.logger import print_task_documentation


@task(pre=[setup.setup_context])
@print_task_documentation
def prepare(ctx):
    """
    Prepare Conan for leet_code-project
    """

    command = ["conan", "--version"]

    CommandExecutor(ctx).execute(command, log="leet_code-conan.prepare.log")


collection = Collection("conan")
collection.add_task(prepare, name="prepare")
