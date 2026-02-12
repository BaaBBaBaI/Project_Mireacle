import sys

def is_prime(n):
    if n <= 1:
        return False
    if n <= 3:
        return True
    if n % 2 == 0 or n % 3 == 0:
        return False
    
    i = 5
    while i * i <= n:
        if n % i == 0 or n % (i + 2) == 0:
            return False
        i += 6
    return True

def main():
    input_data = sys.stdin.read().split()
    
    if len(input_data) >= 2:
        a = int(input_data[0])
        b = int(input_data[1])
        
        if a > b:
            a, b = b, a
            
        for i in range(a, b + 1):
            if is_prime(i):
                print(i, end=" ")
        print()

if __name__ == "__main__":
    main()
