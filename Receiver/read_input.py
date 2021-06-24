def read_sender_input():
    try:
        input_data = input()
        return classify_input(input_data)             
    except EOFError:
        return None,None            
    
def classify_input(input_data):
    attribute = input_data.split(' ')
    if  ValidInput(attribute): 
        temperature = float(attribute[0])
        charge_rate = float(attribute[1])
        return temperature, charge_rate
    raise ValueError("wrong input")
    
def ValidInput(attribute):
    return (len(attribute)==2) and isfloat(attribute[0]) and isfloat(attribute[1])

def isfloat(val):
    try:
        float(val)
        return True
    except ValueError:
        return False
