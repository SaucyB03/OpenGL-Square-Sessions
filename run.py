import subprocess
from subprocess import Popen, PIPE, check_output
import sys

# Get the command-line argument for the number of incorrect implementations
num_incorrect = int(sys.argv[1])

# Get the token and check if it matches
file = open("main.cpp", "r")
# (Done): Change the token on the next line to your token.
# (Done: Record your token in your README file.
if file.readline().strip() != "spinesquare":
    # The token does not match. Print HTML message and exit.
    print("<p>Access denied.</p>")
    file.close()
    raise SystemExit
file.close()

# Compile testing file
try:
    # This is Python's way of calling the command line. We use it to compile the C++ files.
    subprocess.check_output(["gcc -std=c++1y -c main.cpp"],stdin=None,stderr=subprocess.STDOUT,shell=True)
except subprocess.CalledProcessError as e:
    # There were compiler errors in test_cases.cpp. Print out the error message and exit the program.
    print("<p>",e.output,"</p>")
    raise SystemExit
