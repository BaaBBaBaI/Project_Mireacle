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
    d = 77
    n = 119
    
    print("ENTER C: ", end="")
    
    input_data = sys.stdin.read().split()
    
    if input_data:
        c = int(input_data[0])
        m = mod_exp(c, d, n)
        print(f"DECRYPTED: {m}")

if __name__ == "__main__":
    main()
