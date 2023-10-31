from pygdbmi.gdbcontroller import GdbController
from rich.console import Console
from rich.progress import track
import sys

gdbmi = GdbController(command=[
    '/Users/kammce/.conan2/p/b/arm-g724ef3e080948/p/bin/bin/arm-none-eabi-gdb',
    'build/MinSizeRel/except.elf',
    '--interpreter=mi'
], time_to_check_for_additional_output_sec=0.005)

my_stderr = Console(file=sys.stderr)
my_stdout = Console(file=sys.stdout)

my_stderr.log('Connecting to GDB server...')
gdbmi.write('target remote :3333', read_response=False)
my_stderr.log('Resetting device...')
gdbmi.write('mon reset halt', read_response=False)
my_stderr.log('Setting breakpoint to "__cxa_throw" ...')
gdbmi.write('b __cxa_throw', read_response=False)
my_stderr.log('Running to first call of "__cxa_throw" ...')
gdbmi.write('continue', read_response=False)

total_steps = 100000

my_stderr.log(f'Recording {total_steps} total instruction steps...')
my_stdout.out("step,function,address")
for step in track(range(total_steps),
                  console=my_stderr,
                  description='Processing...'):
    response = gdbmi.write('stepi')
    for message in response:
        payload = message['payload']
        if payload and isinstance(payload, dict) and 'frame' in payload:
            my_stdout.out("{},{},{}".format(
                step,
                payload['frame']['func'],
                payload['frame']['addr']
            ))
            if payload['frame']['func'] == "start":
                # Continue from here in order to reach the next call to throw
                gdbmi.write('continue', read_response=False)
