import sys

def gcd(a, b):

    a = abs(a)
    b = abs(b)
    
    while b != 0:
        a, b = b, a % b
    return a

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    idx = 0

    n = int(input_data[idx])
    idx += 1
    
    if n <= 0:
        return

    current_gcd = int(input_data[idx])
    idx += 1

    for i in range(1, n):
        temp = int(input_data[idx])
        idx += 1
        
        current_gcd = gcd(current_gcd, temp)
        if current_gcd == 1:
            break

    print(current_gcd)

if __name__ == "__main__":
    main()
