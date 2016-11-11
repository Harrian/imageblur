import { Meteor } from 'meteor/meteor';
import { LeftImages, RightImages } from '../imports/lib/collections.js';
Meteor.startup(() => {
  LeftImages.remove({});
  RightImages.remove({});
});