import {Component, ElementRef, EventEmitter, Input, OnInit, Output, ViewChild} from '@angular/core';
import {List} from "../../data-access/models/list";

@Component({
  selector: 'list-element',
  templateUrl: './list-element.component.html',
  styleUrls: ['./list-element.component.scss']
})
export class ListElementComponent implements OnInit {

  @Input()
  list : List;

  @Output()
  clickEvent: EventEmitter<List> = new EventEmitter<List>();

  @Output()
  deleteEvent: EventEmitter<List> = new EventEmitter<List>();

  @ViewChild("title")
  inputField : ElementRef;


  constructor() { }

  ngOnInit(): void {
  }

  onListCardClicked(){
    this.clickEvent.emit(this.list);
  }

  onEditClicked(e: Event) {
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

  onDeleteClicked(){
    this.deleteEvent.emit(this.list);
  }


}
