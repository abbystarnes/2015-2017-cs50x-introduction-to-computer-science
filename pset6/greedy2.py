import cs50

def main():
    print("Please give an amount in dollars:")
    userInput = cs50.get_float()
    amount = int(( userInput * 100 ) + 0.5) / float(100)
    count = 0
    while amount > 0:
        amount = int(( amount * 100 ) + 0.5) / float(100)
        print(amount, 'amount')
        if amount >= .25:
            amount = amount - .25
            count = count + 1
        elif amount >= .10:
            amount = amount - .10
            count = count + 1
        elif amount >= .5:
            amount = amount - .5
            count = count + 1
        else:
            amount = amount - .1
            count = count + 1
    print(count, 'count')
        
        
if __name__=="__main__":
    main()        
        
    
    