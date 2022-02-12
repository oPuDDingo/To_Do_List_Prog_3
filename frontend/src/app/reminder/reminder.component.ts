import { Component, OnInit } from '@angular/core';
import {Reminder} from "../../lib/data-access/models/reminder";

@Component({
  selector: 'app-reminder',
  templateUrl: './reminder.component.html',
  styleUrls: ['./reminder.component.scss']
})
export class ReminderComponent implements OnInit {

  reminder : Reminder;

  constructor() { }

  ngOnInit(): void {
  }

}