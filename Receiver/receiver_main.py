from read_input import read_sender_input
from process_input import parameters_statistics
from output import publish_values

class main():
    temperature_lst = []
    charge_rate_lst = []
 
    while True:
        temperature,charge_rate = read_sender_input()
        if temperature == None or charge_rate == None:
            break
        temperature_lst.append(temperature)
        charge_rate_lst.append(charge_rate)
        param_dict = parameters_statistics(temperature_lst,charge_rate_lst)
        publish_values(param_dict)
