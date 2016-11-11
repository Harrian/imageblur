import React, { Component } from 'react';
import { createContainer } from 'meteor/react-meteor-data';
import { LeftImages, RightImages } from '../lib/collections.js';
import Im from './MagicImage.jsx';
// App component - represents the whole app
class App extends Component {
	renderLeftImages(){
	return this.props.leftImages.map((leftImages)=>(
		<Im key={leftImages._id} im={leftImages} />
	));
  }
  renderRightImages(){
	return this.props.rightImages.map((rightImages)=>(
		<Im key={rightImages._id} im={rightImages} />
	));
  }
  render() {
    return (
<div style={{width:100+'%'}}>
  <div className="left-half">
	 Seq
	 {this.renderLeftImages()}
  </div>
  <div className="right-half">
	 Para
	 {this.renderRightImages()}
  </div>
</div>
    );
  }
}

export default createContainer(() => {
  return {
    leftImages: LeftImages.find({}).fetch(),
	rightImages: RightImages.find({}).fetch(),
  };
}, App);