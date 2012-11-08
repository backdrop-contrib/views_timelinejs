var embed_path;

(function ($) {
  Drupal.behaviors.timelineJS = {
    attach: function(context, settings) {
      $.each(Drupal.settings.timelineJS, function(key, timeline) {
        embed_path = timeline['embed_path'];

        if (timeline['processed'] != true) {
          createStoryJS(timeline);
        }
        timeline['processed'] = true;
      });
    }
  }
})(jQuery);

/*
(function($) {
  Drupal.behaviors.timelineJS = {
    attach: function(context, settings) {
      console.log(Drupal.settings);
      // TODO: Make this work with multiple timelines per page
      $.each(Drupal.settings.timelineJS, function(key, timeline) {
        console.log(key);
        console.log(timeline);
        if(VMM.Timeline && timeline['source']) {
          var timelineJS = new VMM.Timeline(
            timeline['embed_id'],
            timeline['width'],
            timeline['height']
          );
          timelineJS.init({
            source: timeline['source'],
            lang: timeline['lang'],
          });
        }
      });
    }
  }
})(jQuery);
*/