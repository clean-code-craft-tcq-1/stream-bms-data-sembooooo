def parameters_statistics(temperature,charge_rate):
      param_dict = {}
      param_dict["temperature"] = calcParam(temperature)
      param_dict["charge_rate"] = calcParam(charge_rate)
      return param_dict
        
def calcParam(battery_parameter):
    params = []
    params.append(min(battery_parameter))
    params.append(max(battery_parameter))
    if len(battery_parameter) >= 5:
        params.append(sum(battery_parameter[-5:])/len(battery_parameter))
    return params     
