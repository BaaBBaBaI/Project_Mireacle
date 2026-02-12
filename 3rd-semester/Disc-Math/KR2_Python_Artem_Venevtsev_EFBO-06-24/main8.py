import sys

def main():
    m = 6075
    a = 106
    c = 1283
    
    print("Enter x0: ", end="")
    
    input_data = sys.stdin.read().split()
    
    if input_data:
        x = int(input_data[0])
        for i in range(3):
            x = (a * x + c) % m
            print(f"x{i+1} = {x}")

if __name__ == "__main__":
    main()
