import cs50

def main():
    while True:
        print("Please give me an int: ")
        n = cs50.get_int()
        if n > 0 and n < 23:
            break
    
    for i in range(0, n):
        count = i + 1
        space = i
            
        while space < (n - 1):
            print(" ", end="")
            space +=1
            
        while count >= 0:
            print("#", end="")
            count-=1
            
        print()
    
    
if __name__=="__main__":
    main()
    
