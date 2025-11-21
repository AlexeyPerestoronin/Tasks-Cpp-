import colorama
import inspect
from enum import Enum
from functools import wraps


class Color(Enum):
    RED = colorama.Fore.RED
    GREEN = colorama.Fore.GREEN
    YELLOW = colorama.Fore.YELLOW
    BLUE = colorama.Fore.BLUE
    MAGENTA = colorama.Fore.MAGENTA
    CYAN = colorama.Fore.CYAN
    BLACK = colorama.Fore.BLACK
    WHITE = colorama.Fore.WHITE
    RESET = colorama.Fore.RESET


class Logger:
    """
    Logger with supporting of color printing
    """

    def __init__(self, color: Color):
        self.__color = color

    def __del__(self):
        print(colorama.Style.RESET_ALL)

    def log_line(self, message: str):
        print(self.__color.value, end='')
        if message[-1] == '\n':
            print(message, end='')
        else:
            print(message, end='\n')
        print(colorama.Style.RESET_ALL, end='')
        return self


SUCCESS = Logger(Color.GREEN)
STATUS = Logger(Color.BLUE)
INFO = Logger(Color.WHITE)
WARNING = Logger(Color.YELLOW)
ERROR = Logger(Color.RED)


def print_task_documentation(func):
    """
    Prints the function's docstring via Logger before execution.
    """

    @wraps(func)
    def wrapper(*args, **kwargs):
        doc = func.__doc__
        if doc:
            STATUS.log_line(doc.strip())
            sig = inspect.signature(func)
            bound_args = sig.bind(*args, **kwargs)
            bound_args.apply_defaults()
            if bound_args.arguments:
                STATUS.log_line("Parameters:")
                for name, value in [item for item in bound_args.arguments.items()][1:]:
                    STATUS.log_line(f" * {name}: {value}")
        return func(*args, **kwargs)

    return wrapper
