import {Component, ElementRef, EventEmitter, Input, OnInit, Output, ViewChild} from '@angular/core';
import {List} from "../../data-access/models/list";

@Component({
  selector: 'list-element',
  templateUrl: './list-element.component.html',
  styleUrls: ['./list-element.component.scss']
})
export class ListElementComponent {

  @Input()
  list : List;

  @Output()
  clickEvent: EventEmitter<List> = new EventEmitter<List>();

  @Output()
  updateEvent: EventEmitter<List> = new EventEmitter<List>();

  @Output()
  deleteEvent: EventEmitter<List> = new EventEmitter<List>();

  @ViewChild("title")
  inputField : ElementRef;


  constructor() { }

  editTitle(e: Event) {
    this.focusIn();
    e.stopPropagation()
  }

  focusIn() : void {
    this.inputField.nativeElement.removeAttribute("readonly");
    this.inputField.nativeElement.focus();
  }

  focusOut() : void {
    this.inputField.nativeElement.setAttribute("readonly", "readonly");
  }

  triggerClick(){
    this.clickEvent.emit(this.list);
  }

  triggerUpdate() {
    this.updateEvent.emit(this.list);
  }

  triggerDelete(){
    this.deleteEvent.emit(this.list);
  }


}
