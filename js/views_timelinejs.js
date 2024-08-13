/**
 * @file
 * Invokes the timeline js plugin.
 */

(function ($) {
  Backdrop.behaviors.timelineJS = {
    attach: function(context, settings) {
      $.each(Backdrop.settings.timelineJS, function(key, timeline) {
        if (timeline['processed'] != true) {
          window.timeline = new TL.Timeline(timeline['embed_id'], timeline['source'], timeline['options']);
        }
        timeline['processed'] = true;
      });
    }
  }
})(jQuery);
