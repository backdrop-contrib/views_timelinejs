Views TimelineJS
================
This module adds a new style plugin for Views which renders result rows as
TimelineJS slides and eras.  The 1.x-1.x branch was created to work with the
TimelineJS3 version of the library.  For more information about TimelineJS visit
https://timeline.knightlab.com/index.html or the GitHub repository
https://github.com/NUKnightLab/TimelineJS3.

Installation
------------
Install this module using the official Backdrop CMS instructions at
https://docs.backdropcms.org/documentation/extend-with-modules.
By default, there are no library files to download because they are served
from the NU Knight Lab CDN.

Optional: If you want to serve the library files from your own site instead of
the CDN, then you need to download the library files.  You MUST put the
TimelineJS library in the sites/all/libraries directory inside your Drupal
installation.  Alternate library locations such as those checked by the
Libraries API module will not work.

You can download or clone the entire TimelineJS3 GitHub repository.
```
git clone --branch master https://github.com/NUKnightLab/TimelineJS3.git
```
If you don't want to download the entire repository, then you can download the
Javascript and CSS files selectively.  The timeline.js and timeline.css files
are required to use TimelineJS.  The library also includes several font
library CSS files that must be downloaded if you want to use them.  In the end,
you need to have the following files in these directories:

1. sites/all/libraries/TimelineJS3/compiled/js/timeline.js
2. sites/all/libraries/TimelineJS3/compiled/css/timeline.css
3. sites/all/libraries/TimelineJS3/compiled/css/fonts/font.FONT-NAME.css
   (optional)

Finally, visit the admin settings form admin/config/development/views_timelinejs
to change the library location setting to Local path.

Issues
----------------------
Bugs and feature requests should be reported in [the Issue Queue](https://github.com/rudy880719/views_timelinejs/issues).

Maintainers
-----------
* [Rodobaldo Perez](https://github.com/rudy880719).

Credits
-------

- Ported to Backdrop CMS by [Rodobaldo Perez](https://github.com/rudy880719)..
- Originally written for Drupal by Juha Niemi (juhaniemi), Olli Erinko (operinko), Jon Peck (fluxsauce), WorldFallz and David Cameron (dcam)

License
-------

This project is GPL v2 software.
See the LICENSE.txt file in this directory for complete text.

<!-- If your project includes other libraries that are licensed in a way that is
compatible with GPL v2, you can list that here too, for example: `Foo library is
licensed under the MIT license.` -->
