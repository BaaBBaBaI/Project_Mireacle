import sys

def gcd(a, b):
    if a < 0: a = -a
    if b < 0: b = -b
    while b != 0:
        temp = b
        b = a % b
        a = temp
    return a

def lcm(a, b):
    if a == 0 or b == 0:
        return 0
    abs_a = abs(a)
    abs_b = abs(b)
    return (abs_a * abs_b) // gcd(abs_a, abs_b)

def main():
    input_data = sys.stdin.read().split()
    
    if len(input_data) >= 2:
        a = int(input_data[0])
        b = int(input_data[1])
        print(lcm(a, b))

if __name__ == "__main__":
    main()
