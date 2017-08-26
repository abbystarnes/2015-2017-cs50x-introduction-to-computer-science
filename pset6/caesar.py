import cs50
import sys

def main():
    # //print("hello")
    if len(sys.argv) <= 1:
        print("Incorrect input. Please rerun caesar and provide an integer as second argument.")
        return 1
    try:
        k = int(sys.argv[1]) 
    except:
        print('Please use an int')
        return 1

    if len(sys.argv) != 2 or k <= 0:
        print("Incorrect input. Please rerun caesar and provide a single integer as the argument.")
        return 1
    else:
        print('plaintext:')
        p = cs50.get_string()
        for i in range(0, len(p)):
            if p[i].isalpha():
                # if p is a lowercase letter letter, print it in lowercase
                if (ord(p[i])) >= 64 and (ord(p[i])) < 91:
                    print(chr((((ord(p[i])) - 65 + k) % 26) + 65), end="")
                elif (ord(p[i])) > 96 and (ord(p[i])) < 123:
                    print(chr((((ord(p[i])) - 97 + k) % 26) + 97), end="")
                else:
                    print("{}".format(((ord(p[i])))), end="")
            else:        
                print(p[i], end="")    
                    
        print()
        return 0

    
if __name__=="__main__":
    main()
    
  
    
    
    #remove line breaks
    #convert back to letters (look at specs)