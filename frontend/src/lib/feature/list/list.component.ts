import {Component, EventEmitter, Input, OnChanges, OnInit, Output, SimpleChanges} from '@angular/core';
import {List} from "../../data-access/models/list";
import {Reminder} from "../../data-access/models/reminder";
import {ArrayUtil} from "../../util/ArrayUtil";

@Component({
  selector: 'list',
  templateUrl: './list.component.html',
  styleUrls: ['./list.component.scss']
})
export class ListComponent implements OnInit, OnChanges {

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

  toDelete: Reminder[] = [];

  constructor() { }

  ngOnInit(): void {
  }

  ngOnChanges(changes: SimpleChanges) {
    while (this.toDelete.length > 0) {
      this.deleteEvent.emit({list: changes.list.previousValue, reminder: this.toDelete.pop()});
    }
  }

  triggerCreate() {
    this.createEvent.emit(this.list);
  }

  triggerUpdate(reminder: Reminder) {
    this.updateEvent.emit({list: this.list, reminder: reminder});
  }

  triggerDelete(e: {reminder: Reminder, type: string}) {
    if(e.type === "countdown") {
      this.toDelete.push(e.reminder);
    }
    else if(e.type === "cancel") {
      ArrayUtil.cutElement(this.toDelete, e.reminder);
    }
    else if(e.type === "delete") {
      ArrayUtil.cutElement(this.toDelete, e.reminder);
      this.deleteEvent.emit({list: this.list, reminder: e.reminder});
    }
  }
}
