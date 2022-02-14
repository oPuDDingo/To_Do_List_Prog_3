import {Component, Input, OnInit} from '@angular/core';
import {List} from "../../lib/data-access/models/list";
import {Reminder} from "../../lib/data-access/models/reminder";

@Component({
  selector: 'app-list',
  templateUrl: './list.component.html',
  styleUrls: ['./list.component.scss']
})
export class ListComponent implements OnInit {

  @Input()
  list : List;

  @Input()
  showAddButton: boolean;

  constructor() { }

  ngOnInit(): void {
  }

  onPlusClicked() {
    this.list.reminders.push({id: 1, title: "", date: "", flagged: false});
  }

  onDeleteClicked(reminder: Reminder) {
    let i: number = this.list.reminders.indexOf(reminder);
    this.list.reminders.splice(i, 1);
  }


}
