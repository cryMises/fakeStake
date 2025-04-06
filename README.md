# fakeStake
### Check The Releases!!! 
A Compilation Of CPP Gambling Games  

To Run The Game In Termux :  
Download Clang and Gh
```
pkg install clang && pkg install gh
```  
Check The Release You Want To Download  
```
gh release ls -R cryMises/fakeStake
```
Download The Release  
```
gh release download <tagName> -D main -R cryMises/fakeStake
```
Go Inside The Directory And Extract  
```
cd main && unzip <fileName>
```
Go To The File
```
cd <fileName> && cd src 
```
Compile
```
clang++ -std=c+++23 -stdlib=libc++ -lc++ -Wall main.cpp -o ./fakeStake && ./fakeStake
```
