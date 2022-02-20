import {Component, EventEmitter, OnInit, Output} from '@angular/core';

@Component({
  selector: 'add-button',
  templateUrl: './add-button.component.html',
  styleUrls: ['./add-button.component.scss']
})
export class AddButtonComponent {

  @Output()
  clickEvent : EventEmitter<Event> = new EventEmitter<Event>();

  constructor() { }

  onClick(e: Event) : void {
    this.clickEvent.emit(e);
  }

}
