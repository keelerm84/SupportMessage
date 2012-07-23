TimeIPS Support Message
=======================
This application is a simple helper utility.  If no member of the support staff is available to take the call, other staff members will take a message.  This application allows them to quickly jot down the relevant information, and notify the support department in a unified manner.

It will generate an email that is sent to the support queue with the pertinent information.  In addition to this, it will send IM's to each of the members of the support team to make sure they are aware a new email has been sent to their queue.

More than anything, this is really just an excuse for me to play with QT and dbus. :)

To Do
-----
This application, while functional, still needs some additional work.

* Password needs to be encrypted
* Error handling and notification system support
* Add support for other IM clients

Credits
-------
SmtpClient code is from bluetiger9.  See https://github.com/bluetiger9/SmtpClient-for-Qt
