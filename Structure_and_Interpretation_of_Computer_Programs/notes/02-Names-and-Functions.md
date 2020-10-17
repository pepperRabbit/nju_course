### Names and Functions

---

- Evaluating Call Expressions

  ![image](https://github.com/pepperRabbit/nju_course/blob/master/Structure_and_Interpretation_of_Computer_Programs/notes/imgs/02-1.png)


- Expression Tree

  ![image](https://github.com/pepperRabbit/nju_course/blob/master/Structure_and_Interpretation_of_Computer_Programs/notes/imgs/02-2.png)



---

- Values

  **Integer**:   2  -3  44

  **Float**:   -3.4  0.2

  **String**:   "hello"

  **Boolean**:   True   False



- Names

  Values can be assigned to **names**

  A name can only be bound to a single value

  ![image](https://github.com/pepperRabbit/nju_course/blob/master/Structure_and_Interpretation_of_Computer_Programs/notes/imgs/02-3.png)



---

- Functions

  They take in some input (known as their **arguments**) and transform it into an output (the **return value**)

  ![image](https://github.com/pepperRabbit/nju_course/blob/master/Structure_and_Interpretation_of_Computer_Programs/notes/imgs/02-4.png)

  

  **Execution rule for** **def Statements**

  1.Create a function with signature <name>**(**<parameters>**)**

  2.Set the body of that function to be everything indented after the first line --> 设置函数主体（第一行之后缩进的所有内容），但不会执行函数

  3.Bind <name> to that function in the current frame

  

  **Procedure for calling/applying user-defined functions (for now)**

  0.

  ![image](https://github.com/pepperRabbit/nju_course/blob/master/Structure_and_Interpretation_of_Computer_Programs/notes/imgs/02-5.png)

  1.Create a new **environment frame**

  ![image](https://github.com/pepperRabbit/nju_course/blob/master/Structure_and_Interpretation_of_Computer_Programs/notes/imgs/02-6.png)

  2.Bind the function's parameters to its arguments in that frame

  ![image](https://github.com/pepperRabbit/nju_course/blob/master/Structure_and_Interpretation_of_Computer_Programs/notes/imgs/02-7.png)

  3.Execute the body of the function in the new environment

  ![image](https://github.com/pepperRabbit/nju_course/blob/master/Structure_and_Interpretation_of_Computer_Programs/notes/imgs/02-8.png)

  



​		

