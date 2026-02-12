import sys

def mod_exp(base, exp, mod):
    result = 1
    base %= mod
    while exp > 0:
        if exp % 2 == 1:
            result = (result * base) % mod
        base = (base * base) % mod
        exp //= 2
    return result

def main():
    e = 5
    n = 119
    
    print("ENTER M: ", end="")
    input_data = sys.stdin.read().split()
    
    if input_data:
        m = int(input_data[0])
        
        if m >= n:
            print(f"ERROR message must be smaller: ({n})")
        else:
            c = mod_exp(m, e, n)
            print(f"ENCRYPTED C: {c}")

if __name__ == "__main__":
    main()
