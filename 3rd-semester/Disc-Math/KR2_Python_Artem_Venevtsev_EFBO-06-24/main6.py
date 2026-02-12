import sys

def extended_gcd(a, b):
    if a == 0:
        return b, 0, 1
    
    d, x1, y1 = extended_gcd(b % a, a)
    x = y1 - (b // a) * x1
    y = x1
    return d, x, y

def main():
    input_data = sys.stdin.read().split()
    
    if len(input_data) >= 3:
        a = int(input_data[0])
        b = int(input_data[1])
        n = int(input_data[2])
        
        g, x, y = extended_gcd(b, n)
        
        if g != 1:
            print("ERR")
        else:
            b_inv = (x % n + n) % n
            result = ((a % n) * b_inv) % n
            print(result)

if __name__ == "__main__":
    main()
