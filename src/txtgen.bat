@echo off
echo Displaying file contents in the current directory and subdirectories... > output.txt
for /r %%f in (*) do (
    echo Displaying contents of %%f >> output.txt
    cat "%%f" >> output.txt
    echo. >> output.txt
)
echo Done. Output saved to output.txt.
pause
@echo off
echo Displaying file contents in the current directory and subdirectories... > output.txt
for /r %%f in (*) do (
    echo Displaying contents of %%f >> output.txt
    cat "%%f" >> output.txt
    echo. >> output.txt
)
echo Done. Output saved to output.txt.
pause

