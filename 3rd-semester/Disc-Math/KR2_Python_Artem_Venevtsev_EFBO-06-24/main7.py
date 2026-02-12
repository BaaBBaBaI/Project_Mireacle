import sys

def main():
    input_data = sys.stdin.read().split()
    
    if input_data:
        n = int(input_data[0])
        
        if n > 1:
            print(f"{n} = ", end="")
            
            first = True
            
            while n % 2 == 0:
                if not first:
                    print(" * ", end="")
                print("2", end="")
                n //= 2
                first = False
            
            i = 3
            while i * i <= n:
                while n % i == 0:
                    if not first:
                        print(" * ", end="")
                    print(i, end="")
                    n //= i
                    first = False
                i += 2
            
            if n > 2:
                if not first:
                    print(" * ", end="")
                print(n, end="")
            
            print()

if __name__ == "__main__":
    main()
