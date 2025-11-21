from invoke import Collection, task

import setup
import leet_code.conan
from utils.logger import print_task_documentation

@task(
    pre=[setup.setup_context],
    help={
        "param1": "boolean parameter",
        "param2": "text parameter",
        "param3": "digit parameter",
    },
)
@print_task_documentation
def full_check(ctx, param1=False, param2="default text", param3=8):
    """
    Project full check (template of combined task)!
    """
    pass


collection = Collection("leet_code")
collection.add_task(full_check, name="full-check")
collection.add_collection(leet_code.conan.collection)
