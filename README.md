# silgy
Silgy is a back-end framework for ultra fast, small and mid-sized web applications. It contains asynchronous (non-blocking) web engine that allows you to compile and link your logic into one executable. It's small enough to fit on free AWS t2.micro instance, together with MySQL server. Typical response time is around 100 us (micro seconds) (see https://budgeter.org performance for proof).  
  
Silgy supports https, typical registered users handling and rudimentary asynchronous services mechanism.  
  
Silgy requires Linux/UNIX computer with C or C++ compiler.  
  
Quick Start Guide:  
  
1. Create a project directory, i.e. web:  
```
mkdir web  
```

2. Set SILGYDIR environment variable to your project directory. If you use bash, that would be in .bash_profile in your home directory:  
```
export SILGYDIR=/home/ec2-user/web  
```
  
Then you need to either restart your shell session or execute above command.  
  
3. In your project directory, create some others:  
```
cd web  
mkdir src  
mkdir bin  
mkdir res  
mkdir resmin  
mkdir logs  
```
  
4. Throw all the files to src. m, mobj and te must have executable flag. In src:  
```
chmod u+x m*  
chmod u+x te  
```
  
5. Go to src and compile everything:  
```
mobj  
```
Make your executable:  
```
m  
```
Run:  
```
sudo te  
```
  
That's it. Your app should now be online.  
  
Your app logic is in silgy_app.cpp and app_process_req() is your main, called with every browser request.
