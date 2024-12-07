# Define file path
file_path = "case.in"

# Initialize containers for the first numbers and the arrays
sum = 0

def test(first_number, other_numbers, idx, curr):
    if idx > len(other_numbers):
        return False

    if curr > first_number:
        return False

    if idx == len(other_numbers):
        if curr == first_number:
            return True
        else:
            return False

    if test(first_number, other_numbers, idx+1, int(str(curr) + str(other_numbers[idx]))):
        return True

    if test(first_number, other_numbers, idx+1, curr * other_numbers[idx]):
        return True

    if test(first_number, other_numbers, idx+1, curr + other_numbers[idx]):
        return True

    return False

# Read and process the file
with open(file_path, "r") as file:
    for line in file:
        # Remove whitespace and split the line
        parts = line.strip().split(":")
        if len(parts) == 2:
            first_number = int(parts[0].strip())
            other_numbers = list(map(int, parts[1].split()))
            
            if(test(first_number, other_numbers, 1, other_numbers[0])):
                sum = sum + first_number
    print(sum)

