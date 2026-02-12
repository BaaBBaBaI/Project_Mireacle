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
    
    if not input_data:
        return
        
    idx = 0
    
    if idx < len(input_data):
        n = int(input_data[idx])
        idx += 1
        
        if n > 0:
            current_lcm = int(input_data[idx])
            idx += 1
            
            for _ in range(1, n):
                next_val = int(input_data[idx])
                idx += 1
                current_lcm = lcm(current_lcm, next_val)
                
            print(current_lcm)

if __name__ == "__main__":
    main()
