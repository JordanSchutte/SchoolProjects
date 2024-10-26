import { Injectable } from '@angular/core';
import { HttpClient, HttpErrorResponse } from '@angular/common/http';
import { Observable, throwError } from 'rxjs';
import { catchError, retry } from 'rxjs/operators';
import { User } from '../models/user';
import { AuthResponse } from '../models/authresponse';
import { Trip } from '../models/trip';

@Injectable({
  providedIn: 'root'
})
export class TripDataService {
  private apiBaseUrl = 'http://localhost:3000/api';

  constructor(private http: HttpClient) { }

  public getTrips(): Observable<Trip[]> {
    const url: string = `${this.apiBaseUrl}/trips`;
    return this.http.get<Trip[]>(url).pipe(
      retry(2),
      catchError(this.handleError)
    );
  }

  public getTrip(tripCode: string): Observable<Trip> {
    const url: string = `${this.apiBaseUrl}/trips/${tripCode}`;
    return this.http.get<Trip>(url).pipe(
      retry(2),
      catchError(this.handleError)
    );
  }

  public addTrip(trip: Trip): Observable<Trip> {
    const url: string = `${this.apiBaseUrl}/trips`;
    return this.http.post<Trip>(url, trip).pipe(
      catchError(this.handleError)
    );
  }

  public updateTrip(tripCode: string, trip: Trip): Observable<Trip> {
    const url: string = `${this.apiBaseUrl}/trips/${tripCode}`;
    return this.http.put<Trip>(url, trip).pipe(
      catchError(this.handleError)
    );
  }

  public deleteTrip(tripCode: string): Observable<any> {
    const url: string = `${this.apiBaseUrl}/trips/${tripCode}`;
    return this.http.delete(url).pipe(
      catchError(this.handleError)
    );
  }

  public login(user: User): Observable<AuthResponse> {
    return this.makeAuthApiCall('login', user);
  }

  public register(user: User): Observable<AuthResponse> {
    return this.makeAuthApiCall('register', user);
  }

  private makeAuthApiCall(urlPath: string, user: User): Observable<AuthResponse> {
    const url: string = `${this.apiBaseUrl}/${urlPath}`;
    return this.http.post<AuthResponse>(url, user).pipe(
      catchError(this.handleError)
    );
  }

  private handleError(error: HttpErrorResponse) {
    if (error.error instanceof ErrorEvent) {
      // A client-side or network error occurred. Handle it accordingly.
      console.error('An error occurred:', error.error.message);
    } else {
      // The backend returned an unsuccessful response code.
      console.error(
        `Backend returned code ${error.status}, ` +
        `body was: ${error.error}`);
    }
    // Return an observable with a user-facing error message.
    return throwError(
      'Something bad happened; please try again later.');
  }
}