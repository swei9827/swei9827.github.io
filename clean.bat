del *.vc /s
del *.obj /s
del *.db /s
del *.pdb /s
del *.ilk /s
del *.idb /s
del *.ipch /s
del *.sdf /s
del *.db /s
del *.pch /s

del *.bin /s
del Thumbs.db /s/a

for /d /r . %d in (.vs) do @if exist "%d" rd /s/q "%d"