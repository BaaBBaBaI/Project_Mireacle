import sys

def gcd(a, b):
    a = abs(a)
    b = abs(b)
    
    while b != 0:
        a, b = b, a % b
        
    return a

def main():
    input_data = sys.stdin.read().split()
    
    if len(input_data) >= 2:
        a = int(input_data[0])
        b = int(input_data[1])
        print(gcd(a, b))

if __name__ == "__main__":
    main()
