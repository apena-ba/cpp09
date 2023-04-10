import subprocess
import random

numbers = random.sample(range(1, 25018), 3000)
arg_list = [str(num) for num in numbers]

try:
    process = subprocess.Popen(["./PmergeMe"] + arg_list, stdout=subprocess.PIPE)

    output, error = process.communicate()
    print(output.decode('utf-8'))
except OSError as e:
    print("Error with exec file\n"
        "Check name (PmergeMe) and permissions")
