### Names and Functions

---

- Evaluating Call Expressions

  <img src="C:\Users\ng_ju\Desktop\新建文件夹\sicp\note\02-1.png" alt="image-20201015214527943" style="zoom:50%;" />



- Expression Tree

  <img src="C:\Users\ng_ju\Desktop\新建文件夹\sicp\note\02-2.png" alt="image-20201015214743984" style="zoom:50%;" />



---

- Values

  **Integer**:   2  -3  44

  **Float**:   -3.4  0.2

  **String**:   "hello"

  **Boolean**:   True   False



- Names

  Values can be assigned to **names**

  A name can only be bound to a single value

  ![image-20201015215214078](C:\Users\ng_ju\Desktop\新建文件夹\sicp\note\02-3.png)



---

- Functions

  They take in some input (known as their **arguments**) and transform it into an output (the **return value**)

  ![image-20201015215724251](C:\Users\ng_ju\Desktop\新建文件夹\sicp\note\02-4.png)

  

  **Execution rule for** **def Statements**

  1.Create a function with signature <name>**(**<parameters>**)**

  2.Set the body of that function to be everything indented after the first line --> 设置函数主体（第一行之后缩进的所有内容），但不会执行函数

  3.Bind <name> to that function in the current frame

  

  **Procedure for calling/applying user-defined functions (for now)**

  0.

  <img src="C:\Users\ng_ju\Desktop\新建文件夹\sicp\note\02-5.png" alt="image-20201015220213998" style="zoom:50%;" />

  1.Create a new **environment frame**

  <img src="C:\Users\ng_ju\Desktop\新建文件夹\sicp\note\02-6.png" alt="image-20201015220243736" style="zoom:50%;" />

  2.Bind the function's parameters to its arguments in that frame

  <img src="C:\Users\ng_ju\Desktop\新建文件夹\sicp\note\02-7.png" alt="image-20201015220304274" style="zoom:50%;" />

  3.Execute the body of the function in the new environment

  <img src="C:\Users\ng_ju\Desktop\新建文件夹\sicp\note\02-8.png" alt="image-20201015220320665" style="zoom:50%;" />

  



​		

