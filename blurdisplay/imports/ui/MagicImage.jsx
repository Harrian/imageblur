import React, { Component, PropTypes } from 'react';

export default class Im extends Component {
  render() {
    return (
      <img src={this.props.im.disklocation}/>
    );
  }
}

Im.propTypes = {
  im: PropTypes.object.isRequired,
};
