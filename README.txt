Services Basic Authentication
=============================

This module adds HTTP basic authentication to the Services module.

*WARNING* HTTP basic authentication username and password are sent as
plain-text and so represent a security weakness. We strongly recommend
using secure (https) traffic for all requests which make use of this
authentication mechanism.


Installation
------------

Unpack the module and place the services_basic_auth folder in your site's
module directory (e.g. sites/all/modules).


CGI/FastCGI compatibility
-------------------------

If you are using the CGI/FastCGI server API, you must apply a patch to your
.htaccess file for basic authentication to work.

You can either apply the included patch "htaccess-fastcgi.patch" or add the
following rewrite rule to your .htaccess file manually:

    RewriteRule .* - [E=HTTP_AUTHORIZATION:%{HTTP:Authorization}]
