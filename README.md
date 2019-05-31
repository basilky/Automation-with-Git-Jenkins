# git-over-http
Sharing a Git repository via http
1.GIT

Version Control System is a software that helps software developers to work together and maintain a complete history of their work.Git,Mercurial,SVN are popular version control systems.Among them Git is the most used and actively developed open source version control system.Git was written by Linus Torvalds,the founder of linux kernel in 2005.

a)	Installing git in ubuntu

Git is cross platform and can be installed easily.In ubuntu,just open terminal and type

sudo apt-get update
sudo apt-get install git

NOTE:There is package called git-core in the repository.The git-core package is a "dummy" package, which has the git package as dependency. This is because the git-core package has been renamed to git.

b)	Creating a bare repository

A bare repository is used for sharing. If you are collaborating with a team of developers, and need a place to share changes to a repo, then you will want to create a bare repository in centralized place where all users can push their changes.Developers will clone the shared bare repo, make changes locally in their working copies of the repo, then push back to the shared bare repo to make their changes available to other users.To create a bare repository named 'myrepo' use following commands.Bare repo contains .git extension in repository name.The option --shared make the repository able to be accessed by anyone.

mkdir git
cd git
git init --bare --shared myrepo.git

NOTE:We cant add files to a bare repository directly.Files can be pushed to bare repository after cloning a working repository.

2.APACHE SERVER

A web server is the software that receives your request to access a web page and serves the web page.Apache HTTP Server is a free and open-source cross-platform web server software. Apache is developed and maintained by an open community of developers under the Apache Software Foundation.

a)	Installing apache and enabling required modules on ubuntu

Apache server can be installed by following command.

sudo apt install apache2

b)	Configuring apache to access the git repository over http

a2enmod is a script that enables the specified module within the apache2 configuration.It is installed along with apache.Enable required modules by 

a2enmod env alias cgi auth_digest

    • env:This module allows for control of internal environment variables that are used by various Apache HTTP Server modules.
    • alias:Provides for mapping different parts of the host file system in the document tree and for URL redirection
    • cgi:Execution of CGI scripts
    • auth_digest:User authentication using MD5 Digest Authentication

Restart apache to apply changes.

sudo service apache2 restart

First change the permissions of the git repository so that apache can access the repository.Use the following command for that.-R option will recursively change the ownership of all repository contents to apache.

chown -R www-data.www-data /path/to/gitrepo

To access git repository over http,we have to define a 'site' for the repository.For that add a new git.conf file to /etc/apache2/site-available

cd /etc/apache2/sites-available
sudo vi git.conf

Now add content to the file(git.conf is provided with documentation).

Here we are using .htpasswd file for authentication.Access to the git repository is allowed only if the username and password matches with that in the .htpasswd file.For that use the following command


htdigest -c /path/to/.htpasswd "Shared Git Repo" username

This command adds the first user.For adding more users,remove the -c argument from syntax.

Create a directory for storing apache logs as given in git.conf

eg:  cd /var/log/apache2
 sudo mkdir git.example.com

Now enable the website as

sudo a2ensite git

Now,our git repository can be cloned as 

git clone http://git.example.com/myrepo.git

But, to redirect the request to the host computer and not the internet,add the url into /etc/hosts,so that the first line will look like 

127.0.0.1	localhost	git.example.com

Now we can clone our repository. 

git clone http://git.example.com/myrepo.git
Output will look like

Cloning into 'myrepo'...
Username for 'http://git.example.com': basil
Password for 'http://basil@git.example.com': 
warning: You appear to have cloned an empty repository.
Checking connectivity... done.

Move to the repository and set our user name and email id.This information is saved in the log files after commit occur.

cd myrepo
git config --global user.email "yourmailid@example.com"
git config --global user.name "Your Name"

Now we have a working copy of the repository.Add contents to the repository as

git add filename
git commit -m "added file"
git push origin master

eg:	touch a
	git add a
	git commit -m "added file a"

output: [master (root-commit) ba4338d] added file a
	1 file changed, 0 insertions(+), 0 deletions(-)
	create mode 100644 a

Now push the changes to the central repository.

git push origin master


output: Username for 'http://git.example.com': basil
	Password for 'http://basil@git.example.com': 
	Counting objects: 3, done.
	Writing objects: 100% (3/3), 207 bytes | 0 bytes/s, done.
	Total 3 (delta 0), reused 0 (delta 0)
	To http://git.example.com/myrepo
	 * [new branch]      master -> master


3.JENKINS

Jenkins is an open source automation server written in Java. Jenkins helps to automate the non-human part of software development process, with continuous integration.Continuous integration (CI) is the practice of merging all developer working copies to a shared mainline several times a day.

a)	Installing Jenkins

Jenkins can be downloaded from https://pkg.jenkins.io/debian-stable/
Move to the directory where jenkins is downloaded and install the package.

eg: sudo gdebi jenkins_2.60.2_all.deb

gdebi will automatically fetch and install required dependency too.

b)	Configuring Jenkins

After installing,jenkins can be accessed through the port 8080(default) or we can create a site for Jenkins using apache.For that go to a web browser and enter

http://localhost:8080

Enter the initial admin password which can be obtained from 

sudo cat /var/lib/jenkins/secrets/initialAdminPassword

After entering password,jenkins will ask you to install plugins.Along with suggested plugins,install git plugin also.
After installing the plugins, jenkins will ask your username and password along with some basic profile info.Provide them and click on finish.

Now start a new project and choose freestyle project.

    • Provide project name and description
    • Choose git as source code management
    • Provide repository url (http://git.example.com/myrepo.git)
    • Add credentials for accessing the repository
    • Choose the given credentials.
    • Tick on poll SCM to build when a commit happens and provide time interval.(eg:* * * * * for every minute)
    • Provide the required build steps.
    • Save settings

Now, jenkins will automatically check whether any commit occurred every minute and execute build steps if any commits had occurred to the repository.





    3) GOOGLE TEST


Google Test is a unit testing library for the C++ programming language.A unit test is the smallest testable part of an application like functions, classes, procedures, interfaces. Unit testing is a method by which individual units of source code are tested to determine if they are fit for use.

    a) Installing GOOGLE TEST

In terminal,

sudo apt-get install libgtest-dev
sudo apt-get install cmake
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
sudo cp *.a /usr/lib

b)	Running a basic test

Move to some directory and create a function to be tested.
eg:what.h provided with documentation.
Now create a test file to test the function.
eg:tests.cpp provided with documentation

Create a CMakeLists.txt file on the same directory to compile the tests.(Provided with documentation)

Now,type the following in terminal to execute tests.

cmake CMakeLists.txt
make
./runTests
Sample Output:
[==========] Running 2 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 2 tests from Factorialtest
[ RUN      ] Factorialtest.PositiveNos
[       OK ] Factorialtest.PositiveNos (0 ms)
[ RUN      ] Factorialtest.Zero
[       OK ] Factorialtest.Zero (0 ms)
[----------] 2 tests from Factorialtest (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test case ran. (1 ms total)
[  PASSED  ] 2 tests.
