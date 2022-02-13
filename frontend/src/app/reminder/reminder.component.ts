import {Component, EventEmitter, Input, OnInit, Output} from '@angular/core';
import {Reminder} from "../../lib/data-access/models/reminder";

@Component({
  selector: 'app-reminder',
  templateUrl: './reminder.component.html',
  styleUrls: ['./reminder.component.scss']
})
export class ReminderComponent implements OnInit {

  @Input()
  reminder : Reminder;

  @Output()
  deleteClicked: EventEmitter<Reminder> = new EventEmitter<Reminder>();

  constructor() { }

  ngOnInit(): void {
  }

  onDeleteClicked(){
    this.deleteClicked.emit(this.reminder);
  }
}
