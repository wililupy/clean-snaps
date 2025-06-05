# clean-snaps
C++ code to remove disabled Snaps from a system using Snaps.<br>
This is useful to free up space since snaps will only self-delete after 3 revisions. <br>
To compile run <br>
```g++ -o clean-snaps clean-snap.cpp``` 
<br>
Then run: <br>
```sudo ./clean-snaps``` 
<br>
This will clean the disabled snaps from the system.<br>
You can add this command to a location on your system in the `$PATH` so that you can run this from any prompt.
