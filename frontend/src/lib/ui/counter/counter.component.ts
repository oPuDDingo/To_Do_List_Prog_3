import {Component, Input, OnInit} from '@angular/core';

@Component({
  selector: 'counter',
  templateUrl: './counter.component.html',
  styleUrls: ['./counter.component.scss']
})
export class CounterComponent {

  @Input()
  count: number;

  constructor() { }

}
