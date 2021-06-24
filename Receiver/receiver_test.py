import unittest
import read_input
import process_input

class test_sender_data(unittest.TestCase):
    
  def test_extra_input(self):
      with self.assertRaises(ValueError) as context:
            read_input.classify_input("102 103 104")
      self.assertTrue('wrong input' in str(context.exception))
      
  def test_string_input(self):
      with self.assertRaises(ValueError) as context:
            read_input.classify_input("ab cd")
      self.assertTrue('wrong input' in str(context.exception))  
      
  def test_empty_input(self):
      with self.assertRaises(ValueError) as context:
            read_input.classify_input(" ")
      self.assertTrue('wrong input' in str(context.exception))
      
  def test_wrong_temp(self):
      with self.assertRaises(ValueError) as context:
            read_input.classify_input("ab 18")
      self.assertTrue('wrong input' in str(context.exception))  

  def test_wrong_chargeRate(self):
      with self.assertRaises(ValueError) as context:
            read_input.classify_input("102 CR")
      self.assertTrue('wrong input' in str(context.exception))
      
  def test_single_input(self):
      with self.assertRaises(ValueError) as context:
            read_input.classify_input("133.33")
      self.assertTrue('wrong input' in str(context.exception))  

  def test_avg_less_val(self):
      self.assertTrue(len(process_input.calcParam([133.33 , 144, 111])),2)    
      
  def test_avg_five_val(self):
      self.assertTrue(len(process_input.calcParam([133.33 , 144, 111, 129.4, 133.6])),3)

  def test_min(self):
      self.assertTrue(process_input.calcParam([133.33 , 144, 111, 129.4, 133.6])[0],111) 

  def test_max(self):
      self.assertTrue(process_input.calcParam([133.33 , 144, 111, 129.4, 133.6])[1],144) 

  def test_avg(self):
      self.assertTrue(process_input.calcParam([10,10,10,10,10])[2],10)
          

#if __name__ == '__main__':
  #unittest.main()
        
