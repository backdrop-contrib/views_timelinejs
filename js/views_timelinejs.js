/**
 * @file
 * Invokes the TimelineJS library for each timeline listed in Drupal settings.
 */

(function (Drupal) {
  Drupal.behaviors.viewsTimelineJS = {
    attach: function (context, settings) {
      settings.TimelineJS.forEach(function(timeline, key) {
        if (timeline['processed'] != true) {
          window.timeline = new TL.Timeline(timeline['embed_id'], timeline['source'], timeline['options']);
        }
        timeline['processed'] = true;
      });
    }
  };
})(Drupal);
