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
  reminderDeleted: EventEmitter<Reminder> = new EventEmitter<Reminder>();

  constructor() { }

  ngOnInit(): void {
  }

  onPlusClicked() {
    this.list.reminders.push({id: 1, title: "", date: "", flagged: false});
  }

  onDeleteClicked(reminder: Reminder) {
    let i: number = this.list.reminders.indexOf(reminder);
    this.list.reminders.splice(i, 1);
    if(this.isFilterList){
      this.reminderDeleted.emit(reminder);
    }
  }



}
