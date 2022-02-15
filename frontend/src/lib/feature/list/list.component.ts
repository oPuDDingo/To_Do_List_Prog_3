import {Component, EventEmitter, Input, OnInit, Output} from '@angular/core';
import {List} from "../../data-access/models/list";
import {Reminder} from "../../data-access/models/reminder";

@Component({
  selector: 'list',
  templateUrl: './list.component.html',
  styleUrls: ['./list.component.scss']
})
export class ListComponent implements OnInit {

  @Input()
  list : List;

  @Input()
  isFilterList: boolean;

  @Output()
  createEvent: EventEmitter<List> = new EventEmitter<List>();

  @Output()
  updateEvent: EventEmitter<{list: List, reminder: Reminder }> = new EventEmitter<{list: List, reminder: Reminder }>();

  @Output()
  deleteEvent: EventEmitter<{list: List, reminder: Reminder }> = new EventEmitter<{list: List, reminder: Reminder }>();

  constructor() { }

  ngOnInit(): void {
  }

  triggerCreate() {
    this.createEvent.emit(this.list);
  }

  triggerUpdate(reminder: Reminder) {
    this.updateEvent.emit({list: this.list, reminder: reminder});
  }

  triggerDelete(reminder: Reminder) {
    this.deleteEvent.emit({list: this.list, reminder: reminder});
  }


}
