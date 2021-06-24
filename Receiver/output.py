def publish_values(param_dict):
    print_output("Temperature",param_dict["temperature"])
    print_output("Charge_rate",param_dict["charge_rate"])   
    
    
def print_output(param_name,param_values):
    avg_val = ""
    if len(param_values) == 3:
        avg_val = " Average of last five values: " + str(param_values[2])
    print(f'{param_name:>5} - Min value: {str(param_values[0]):<5}  Max value: {str(param_values[1]):<5}  {avg_val}') 
