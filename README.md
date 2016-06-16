Views TimelineJS
================
This module adds a new style plugin for Views which renders result rows as
TimelineJS slides and eras.  The 7.x-3.x branch was created to work with the
TimelineJS3 version of the library.  For more information about TimelineJS visit
https://timeline.knightlab.com/index.html or the GitHub repository
https://github.com/NUKnightLab/TimelineJS3.

Installation
------------
Download the module from http://drupal.org/project/views_timelinejs and enable
it.  By default, there are no library files to download because they are served
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

Upgrading
---------
If you are upgrading this module from version 7.x-1.x then make sure you test
your view and reconfigure it before deploying to a production environment!  Much
of the plugin's functionality was changed in the upgrade to TimelineJS3.
Version 3 of the library offers several nice enhancements over version 2.  The
plugin has received a lot of updates in order to take full advantage of the new
library.  Some settings have been changed or removed.  New settings have been
added.  The fact that the Date field setting has been split into separate Start
date and End date field settings means that all existing views that were built
with version 7.x-1.x will need to be reconfigured for 7.x-3.x.

Using the Plugin
----------------
1. Create a new view and change the display format to "TimelineJS".
2. Click "Add" in the Fields section of the Views interface to add all the
   desired fields to the view. Once fields have been added, they will be
   available for field mappings.
3. Format the fields used for the timeline as desired. For example, if you want
   the headline to link to the entity it represents use the "Link this field to
   the original piece of content" option in the field's settings.  Likewise if
   you want to strip tags from the body text, use the "Rewrite results" ->
   "Strip HTML tags" option in that field's settings.
4. Click the Settings link in the Format section.  Edit the general
   configuration of the timeline display.  Then add field mappings.  If you do
   not select a field mapping for all the required elements, you will get errors
   on the view.  See the section on "Configuring the Plugin" for more
   information.
5. Click "Save" in the view to complete the configuration. The preview display
   on the Views edit interface shows the data used by TimelineJS.  To see the
   TimelineJS display, access the view page that was just created.

Configuring the Plugin
----------------------
The settings form, accessed by clicking the Settings link in the Format section,
is divided into three sections.  The TimelineJS Options and Additional Options
sections contain settings for controlling the timeline presentation.  The third
section is where you add field mappings.

A field mapping tells Views to output one of the data fields to a specific
TimelineJS object property.  These mappings more or less conform to the fields
in the TimelineJS Google Spreadsheet Template.  Unlike in version 7.x-1.x of the
module, the new plugin does not restrict the types of Drupal data fields that
may be used for mappings.  You may use any type of field with any configuration
and rewriting for any property, provided that the field output matches the type
of data expected by TimelineJS, with a few exceptions.

Here is a list of the available mappings, with suggestions for the data fields
you could use.
* Headline - The selected field may contain any text, including HTML markup.

* Body text - The selected field may contain any text, including HTML markup.

* Start date - The selected field should contain a string representing a date
  conforming to a [PHP supported date and time format]
  (http://php.net/manual/en/datetime.formats.php).

  The field should contain a single date, which means if you use a Date field
  then you need to configure it to only output the Start date value.  If you
  want to display end dates, then you will have to add the field a second time.
  Obviously, that second field should be configured to only output the End date
  value.

* End date - See the Start date mapping above.

* Display date - The selected field should contain a string.  TimelineJS will
  display this value instead of the values of the start and end date fields.

  This is possibly most useful for overriding the display of a Date field when
  you want to display a partial date.  The Date module requires you to input a
  complete date with a year, month, and day value.  That is because the MySQL
  datetime data type has this same restriction.  If you want to display a
  partial date, e.g. "June 2016", then input 06/01/2016 into the date field,
  optionally giving it a range with an end date of 06/30/2016, then enter "June
  2016" in the Display date field to format it the way you want.

* Background image - The selected field should contain a raw URL to an image.
  Special handling is included for Image fields because they have no raw URL
  formatter.

  There is another contributed module, Image URL Formatter, that adds a field
  formatter for outputting a raw Image URL.  You may use it if you want, but it
  should not be necessary with the special handling.  Use the default Image
  field formatter and the plugin will extract the URL from the img tag's src
  attribute.

  Of course, Link fields or Text fields will work for this mapping, along with
  any other field that can output a string containing a raw URL to an image.

* Media URL - The selected field should contain a raw URL to a media resource.
  See the [media types documentation]
  (https://timeline.knightlab.com/docs/media-types.html) for a list of supported
  types. Blockquote and iframe HTML are not currently supported by this plugin.
  Special handling is included for Image fields because they have no raw URL
  formatter.

* Media caption - The selected field may contain any text, including HTML
  markup.

* Media credit - The selected field may contain any text, including HTML markup.

* Group - The selected field may contain any text.

  The TimelineJS documentation makes no mention of HTML being allowed in group
  text, but it will be added to the output.  This plugin does not strip tags
  from groups in order to allow you to format them if desired.

  If you use a Taxonomy reference field for this purpose, it is recommended that
  you format the field as Plain text, rather than as a Link.  The links will not
  work correctly and they may cause the group text to be styled strangely.

* Type - Determines the type of timeline entity that is rendered: event, title
  slide, or era. This plugin recognizes a limited set of string values to
  determine the type.

  1. "title" or "timeline_title_slide" will cause a views data row to be
     rendered as a TimelineJS title slide. Only one title slide can be created
     per timeline. Additional title slides will overwrite previous slides.
  2. "era" or "timeline_era" rows will be rendered as TimelineJS eras.
  3. By default, a row with an empty value or any other input will be rendered
     as a regular event slide.

  Again, where these strings come from doesn't matter.  You could create a
  content type with a List field configured with a radio button widget.
  Alternatively, you could create separate content types for events, title
  slides, and eras, making sure they have machine names that match the accepted
  values.  Then add the Content: Type as a view field and map it to the Type
  property.

* Unique ID - The selected field should contain a string value which is unique
  among all slides in your timeline, e.g. a node ID. If not specified,
  TimelineJS will construct an ID based on the headline, but if you later edit
  your headline, the ID will change. Unique IDs are used when the hash_bookmark
  option is used.

  If you don't need to make sure your slides have permanent links, you probably
  don't need to configure this mapping.

Maintainers
-----------
* Juha Niemi (juhaniemi)
* Olli Erinko (operinko)
* Jon Peck (fluxsauce)
* WorldFallz
* David Cameron (dcam)
