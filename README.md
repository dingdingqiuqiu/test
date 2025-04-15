create a new repository on the command line

```zsh
echo "# test" >> README.md
git init
git add README.md
git commit -m "first commit"
git branch -M main
git remote add origin git@github.com:dingdingqiuqiu/test.git
git push -u origin main

```
or push an existing repository from the command line
```zsh
git remote add origin git@github.com:dingdingqiuqiu/test.git
git branch -M main
git push -u origin main
```
